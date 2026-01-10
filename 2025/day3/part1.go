package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
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

		largest := '0'
		secondLargest := '0'

		// loop through each battery in the bank to find the largest digit
		// last digit is skipped because there is no other digit after it to form a valid joltage
		for i := 0; i < len(line)-1; i++ {

			currentChar := rune(line[i])

			// if the current digit is the largest digit, find the largest digit among the digits after it to form a joltage
			if currentChar > largest {
				largest = currentChar

				// reset second battery value
				secondLargest = '0'

				for j := i + 1; j < len(line); j++ {
					current := rune(line[j])

					if current > secondLargest {
						secondLargest = current
					}
				}
			}

		}

		joltage := string(largest) + string(secondLargest)

		joltageNum, err := strconv.Atoi(joltage)

		if err != nil {
			log.Fatalf("can't convert joltage to num")
		}

		sum = sum + joltageNum
	}

	fmt.Println("sum", sum)
}
