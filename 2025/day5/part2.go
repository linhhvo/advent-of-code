package main

import (
	"bufio"
	"cmp"
	"fmt"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

// convert ID range limits to integers
func getRange(line string) (int, int) {
	splitLine := strings.Split(line, "-")

	lower, err := strconv.Atoi(splitLine[0])

	if err != nil {
		log.Fatalf("can't convert lower to number")
	}

	upper, err := strconv.Atoi(splitLine[1])

	if err != nil {
		log.Fatalf("can't convert upper to number")
	}

	return lower, upper
}

func main() {
	file, err := os.Open("input.txt")
	// file, err := os.Open("sample.txt")

	if err != nil {
		log.Fatalf("can't open file: %s", err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var ranges []string

	for scanner.Scan() {
		line := scanner.Text()

		// end loop when reaches empty line
		if line == "" {
			break
		}

		ranges = append(ranges, line)
	}

	// sort ranges in ascending order based on lower limit
	slices.SortFunc(ranges, func(range1, range2 string) int {
		lower1, _ := getRange(range1)
		lower2, _ := getRange(range2)

		return cmp.Compare(lower1, lower2)
	})

	count := 0
	upperMax := 0

	type limit struct {
		lower int
		upper int
	}

	var groupings [][]limit
	var overlapGroup []limit

	for i := range ranges {
		lower, upper := getRange(ranges[i])

		fmt.Println("overlapGroup begin loop", overlapGroup)

		// if current range doesn't overlap with the previous range, add the overlapGroup to the list of all groupings
		if lower > upperMax && len(overlapGroup) > 0 {
			groupings = append(groupings, overlapGroup)
			overlapGroup = []limit{}
		}

		// when overlapGroup is empty or when current range overlaps with the previous range, add it to the existing overlapGroup
		overlapGroup = append(overlapGroup, limit{lower, upper})

		// get the range maximum of the whole overlapGroup
		upperMax = slices.MaxFunc(overlapGroup, func(a, b limit) int {
			return cmp.Compare(a.upper, b.upper)
		}).upper
	}

	// add the last group if there is no more ID range to read
	if len(overlapGroup) > 0 {
		groupings = append(groupings, overlapGroup)
	}

	fmt.Println("groupings", groupings)

	for i := range groupings {
		rangeCount := 0
		// if there is no overlap range
		if len(groupings[i]) == 1 {
			rangeCount = groupings[i][0].upper - groupings[i][0].lower + 1
		} else { // if there are overlap ranges
			maxLimit := slices.MaxFunc(groupings[i], func(a, b limit) int {
				return cmp.Compare(a.upper, b.upper)
			})

			rangeCount = maxLimit.upper - groupings[i][0].lower + 1
		}

		count = count + rangeCount
	}

	fmt.Println("result:", count)

}
