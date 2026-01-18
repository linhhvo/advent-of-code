package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
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
	var ingredients []int

	for scanner.Scan() {
		line := scanner.Text()

		// skip empty line separator
		if line == "" {
			continue
		}

		if strings.Contains(line, "-") {
			ranges = append(ranges, line)
		} else {
			ingredientID, err := strconv.Atoi(line)

			if err != nil {
				log.Fatalf("can't convert ingredient to number")
			}

			ingredients = append(ingredients, ingredientID)
		}
	}

	count := 0

	// go through each ingredient ID and check if it's within any of the given ranges
	for i := range ingredients {
		for j := range ranges {
			lower, upper := getRange(ranges[j])

			if ingredients[i] >= lower && ingredients[i] <= upper {
				count++
				break //stop checking the ranges
			}
		}
	}

	fmt.Println("fresh ingredients:", count)

}
