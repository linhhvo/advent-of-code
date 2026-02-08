package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("input")
	// file, err := os.Open("example")

	if err != nil {
		panic(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var matrix [][]string

	for scanner.Scan() {
		line := scanner.Text()
		row := strings.Split(line, "")
		matrix = append(matrix, row)
	}

	type position struct {
		row int
		col int
	}

	connectedBeams := make(map[position][]position)
	var startPos position

	for i := range matrix {
		for j := range matrix[i] {
			if matrix[i][j] == "S" {
				matrix[i+1][j] = "|"
				startPos = position{i + 1, j}
			} else if matrix[i][j] == "^" && matrix[i-1][j] == "|" {
				// split beam
				matrix[i][j-1] = "|"
				matrix[i][j+1] = "|"
				// connect the new splitted beams to the source beam
				source := position{row: i - 1, col: j}
				connectedBeams[source] = append(connectedBeams[source], position{i, j - 1})
				connectedBeams[source] = append(connectedBeams[source], position{i, j + 1})
			} else if i > 0 && matrix[i-1][j] == "|" {
				matrix[i][j] = "|"
				// connect to the source beam
				source := position{row: i - 1, col: j}
				connectedBeams[source] = append(connectedBeams[source], position{i, j})
			}
		}
	}

	var getTimeline func(p position) int

	memo := make(map[position]int)

	getTimeline = func(p position) int {
		_, visited := memo[p]               //check if exists in memo
		_, hasNeighbor := connectedBeams[p] //check if current position has any neighbor

		// if reach the end, there is only 1 path
		if hasNeighbor == false {
			return 1
		}

		// if exists in memo, use value in memo
		if visited {
			return memo[p]
		}

		// if position has not been visited
		for i := range connectedBeams[p] {
			n := connectedBeams[p][i]
			memo[p] = memo[p] + getTimeline(n)
		}
		return memo[p]
	}

	timelineCount := getTimeline(startPos)

	fmt.Println("timeline count: ", timelineCount)
}
