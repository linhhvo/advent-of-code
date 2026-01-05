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

	// if an ID has even length, compare 2 halves of the ID
	// all ID that have odd length is valid
	if len(id)%2 == 0 {
		mid := len(id) / 2
		firstHalf := id[:mid]
		secondHalf := id[mid:]

		if firstHalf == secondHalf {
			return false
		}
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

		// if the range only consists of odd length ID, skip since all ID in this range is valid
		if len(rangeStr[0])%2 != 0 && len(rangeStr[1])%2 != 0 {
			continue
		}

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

