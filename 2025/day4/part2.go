package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

// get all 8 adjacent positions and count how many of them contain a paper roll
func getNeighborCount(grid [][]string, row int, col int) int {
	neighbors := []string{grid[row-1][col-1], grid[row-1][col], grid[row-1][col+1], grid[row][col-1], grid[row][col+1], grid[row+1][col-1], grid[row+1][col], grid[row+1][col+1]}

	count := 0

	for i := range neighbors {
		if neighbors[i] == "@" {
			count++
		}
	}
	return count
}

func main() {
	// file, err := os.Open("sample.txt")
	file, err := os.Open("input.txt")

	if err != nil {
		log.Fatalf("can't open file: %s", err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	var grid [][]string
	var row []string

	var padding []string

	for scanner.Scan() {
		line := scanner.Text()
		row = strings.Split(line, "")

		// create a padding row with no paper roll
		padding = make([]string, len(row)+2)
		for i := range padding {
			padding[i] = "."
		}

		// add padding to the first row
		if len(grid) == 0 {
			grid = append(grid, padding)
		}

		row = append([]string{"."}, row...) // add padding to the first column
		row = append(row, ".")              // adding padding to the last column

		// add input row to grid
		grid = append(grid, row)
	}

	// add padding to the last row
	grid = append(grid, padding)

	count := 0
	accessible := true

	type position struct {
		rowIndex int
		colIndex int
	}

	for {
		if accessible == false {
			break
		}

		removable := []position{}

		for i := 1; i < len(grid)-1; i++ {
			for j := 1; j < len(row)-1; j++ {
				if grid[i][j] != "@" {
					continue
				}

				if getNeighborCount(grid, i, j) < 4 {
					count++
					removable = append(removable, position{i, j})
				}
			}
		}

		if len(removable) > 0 {
			for k := range len(removable) {
				grid[removable[k].rowIndex][removable[k].colIndex] = "."
			}
		} else {
			accessible = false
		}
	}
	fmt.Println("count:", count)
}
