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
		characters := strings.Split(line, "")
		matrix = append(matrix, characters)
	}

	// get the list of operands for each equation
	var operandList [][]int
	var operands []int

	for i := range matrix[0] {
		var num int
		var concatStr string

		// concat digits vertically to form an operand
		for j := range len(matrix) - 1 {
			concatStr = concatStr + matrix[j][i]
		}

		// clean and convert to integer
		concatStr = strings.TrimSpace(concatStr)
		num, _ = strconv.Atoi(concatStr)

		if num == 0 { // at the end of a worksheet column
			operandList = append(operandList, operands)
			operands = []int{}
		} else {
			operands = append(operands, num)
		}
	}

	// add the last column
	if len(operands) > 0 {
		operandList = append(operandList, operands)
	}

	// clean the list of operators
	operators := slices.DeleteFunc(matrix[len(matrix)-1], func(w string) bool {
		return w == " "
	})

	finalSum := 0

	for i := range operators {
		if operators[i] == "+" {
			sum := 0
			for j := range operandList[i] {
				sum = sum + operandList[i][j]
			}
			finalSum = finalSum + sum
		} else {
			product := 1
			for j := range operandList[i] {
				product = product * operandList[i][j]
			}
			finalSum = finalSum + product
		}
	}

	fmt.Println("result:", finalSum)
}
