package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

func main() {
	file, err := os.Open("input.txt")
	// file, err := os.Open("sample.txt")

	if err != nil {
		log.Fatalf("failed to open file: %s", err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	sum := 0

	// read file line by line
	for scanner.Scan() {
		line := scanner.Text()

		var batteries []string

		startPos := 0

		for remainingDigits := 11; remainingDigits >= 0; remainingDigits-- {
			// construct a sub string from the start position until the last possible digit
			subStr := line[startPos:(len(line) - remainingDigits)]
			digits := strings.Split(subStr, "")                                // split into slices
			batteries = append(batteries, slices.Max(digits))                  // add the largest digit to the sequence
			startPos = startPos + slices.Index(digits, slices.Max(digits)) + 1 // update the sub string starting position
		}

		joltage, err := strconv.Atoi(strings.Join(batteries, ""))

		if err != nil {
			log.Fatalln("can't convert joltage to number")
		}

		sum = sum + joltage
	}

	fmt.Println("sum", sum)
}
