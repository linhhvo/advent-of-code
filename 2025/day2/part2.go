package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

// convert range start and end to integer for iteration
func getRangeNums(nums []string) (int, int) {
	start, err := strconv.Atoi(nums[0])

	if err != nil {
		log.Fatalf("can't convert range start to number")
	}

	end, err := strconv.Atoi(nums[1])

	if err != nil {
		log.Fatalf("can't convert range end to number")
	}

	return start, end
}

// check if an ID is valid
func isValid(num int) bool {
	id := strconv.Itoa(num)

	mid := len(id) / 2

	// assess each pattern containing the number of digits from 1 to half of the id's length
	i := 1
	for i <= mid {
		pattern := id[:i]
		patternCount := strings.Count(id, pattern)

		// the ID is invalid if the ID consists of only the repeated pattern
		if patternCount > 1 && patternCount*len(pattern) == len(id) {
			return false
		}
		i++
	}
	return true
}

func main() {
	sum := 0

	data, err := os.ReadFile("input.txt")
	// data, err := os.ReadFile("sample.txt")

	if err != nil {
		log.Fatalf("failed to read file: %s", err)
	}

	// remove the last end of line character
	trimData := strings.TrimRight(string(data), "\r\n")

	for idRange := range strings.SplitSeq(trimData, ",") {

		// get range start and end as strings
		rangeStr := strings.Split(idRange, "-")

		start, end := getRangeNums(rangeStr)

		i := start
		for i <= end {
			if !isValid(i) {
				sum = sum + i
			}
			i++
		}
	}

	fmt.Println("sum:", sum)
}
