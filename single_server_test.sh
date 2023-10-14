PORT_BASE=1234
HOST_BASE=127.0.0.1
MAX_ITER=500

function get_cs() {
	echo http://$HOST_BASE:$PORT_BASE
}

function get_key() {
	echo "key-$(shuf -i 1-$MAX_ITER -n 1)"
}

function query_key() {
	local key=$1
	local exist=$2
	local expect="{\"$key\":\"value $(echo $key | sed 's/.*-//')\"}"
	echo "Getting $key from cache server..."
	local response
	response=$(curl -s -w "\n%{http_code}" $(get_cs)/$key)
	local result=$(echo "$response" | head -n 1)
	local status_code=$(echo "$response" | tail -n 1)
	if [[ $exist == 1 ]]; then
		if [[ $status_code -ne 200 ]] || [[ $result != $expect ]]; then
			echo "Error: Invalid response"
			echo "expect:$expect $status_code"
			echo "got:$result $status_code"
			return 1
		fi
	else
		if [[ $status_code -ne 404 ]]; then
			echo "Error: Expect 404"
			return 1
		fi
	fi
	return 0
}

function test_set() {
	local i=1
	while [[ $i -le $MAX_ITER ]]; do
		echo "Setting key-$i to cache server..."
		status_code=$(curl -s -o /dev/null -w "%{http_code}" -XPOST -H "Content-type: application/json" -d "{\"key-$i\": \"value $i\"}" $(get_cs))
		if [[ $status_code -ne 200 ]]; then
			echo "Error: Expected status code 200 but got $status_code"
			return 1
		fi
		((i++))
	done
	return 0
}

function test_get() {
	local count=$((MAX_ITER / 10))
	local i=0
	while [[ $i -lt $count ]]; do
		if ! query_key $(get_key) 1; then
			return 1
		fi
		((i++))
	done
	return 0
}

function test_delete() {
	local count=$((MAX_ITER / 10 * 9))
	keys=()
	while [[ ${#keys[@]} -lt $count ]]; do
		key="key-$(shuf -i 1-$MAX_ITER -n 1)"
		if ! [[ " ${keys[@]} " =~ " ${key} " ]]; then
			keys+=("$key")
		fi
	done
	for key in "${keys[@]}"; do
		echo "Deleting a random key from cache server..."
		response=$(curl -XDELETE -s -w "\n%{http_code}" $(get_cs)/$key)
		result=$(echo "$response" | head -n 1)
		status_code=$(echo "$response" | tail -n 1)
		# 检查状态码和结果
		expect=1
		if [[ $status_code -ne 200 ]] || [[ $result != $expect ]]; then
			echo "Error: Invalid response"
			echo "expect:$expect $status_code"
			echo "got:$result $status_code"
			return 1
		fi
		((i++))
	done
	local count=$((MAX_ITER / 10))
	local i=0
	while ((i < count)); do
		local key=$(get_key)
		local exist=1
		[[ " ${keys[@]} " =~ " ${key} " ]] && exist=0
		! query_key $key $exist && return 1
		((i++))
	done

}

function run_test() {
	local test_function=$1
	local test_name=$2

	echo "Starting $test_name test..."
	if ! $test_function; then
		echo "$test_name test failed."
		return 1
	else
		echo "$test_name test passed."
		return 0
	fi
}

declare -a test_order=(
	"test_set"
	"test_get"
	"test_set again"
	"test_delete"
)

declare -A tests=(
	["test_set"]="set"
	["test_get"]="get"
	["test_set again"]="set again"
	["test_delete"]="delete"
)

declare -A test_results
pass_count=0

for test in "${test_order[@]}"; do
	if run_test "$test" "${tests[$test]}"; then
		((pass_count++))
		test_results["$test"]="passed"
	else
		test_results["$test"]="failed"
	fi
done

echo "$pass_count tests passed in total."

for test in "${!test_results[@]}"; do
	echo "$test: ${test_results[$test]}"
done