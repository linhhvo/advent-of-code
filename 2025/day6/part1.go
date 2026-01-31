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

	file, err := os.Open("input")
	// file, err := os.Open("example")

	if err != nil {
		log.Fatalf("failed to open file: %s", err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var matrix [][]string

	// read file line by line
	for scanner.Scan() {

		line := scanner.Text()
		components := strings.Split(line, " ")
		components = slices.DeleteFunc(components, func(w string) bool {
			return w == ""
		})

		matrix = append(matrix, components)
	}

	finalSum := 0

	for i := range matrix[0] {
		// addition
		if matrix[len(matrix)-1][i] == "+" {
			sum := 0
			for j := range len(matrix) - 1 {
				operand, _ := strconv.Atoi(matrix[j][i])
				sum = sum + operand
			}
			finalSum = finalSum + sum
		} else { // multiplication
			product := 1
			for j := range len(matrix) - 1 {
				operand, _ := strconv.Atoi(matrix[j][i])
				product = product * operand
			}
			finalSum = finalSum + product
		}
	}

	fmt.Println("result:", finalSum)
}
