package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("input")

	if err != nil {
		log.Fatalf("file error: %s", err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var matrix [][]string

	for scanner.Scan() {
		line := scanner.Text()
		row := strings.Split(line, "")
		matrix = append(matrix, row)
	}

	count := 0

	for i := range len(matrix) {
		for j := range len(matrix[i]) {
			if matrix[i][j] == "S" {
				matrix[i+1][j] = "|"
			} else if matrix[i][j] == "^" && matrix[i-1][j] == "|" { // encounter spliter
				matrix[i][j-1] = "|"
				matrix[i][j+1] = "|"
				count++
			} else if i > 0 && matrix[i-1][j] == "|" { // pass through free space
				matrix[i][j] = "|"
			}
		}
	}

	fmt.Println("count: ", count)

}
