package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	dial := 50
	password := 0
	// file, err := os.Open("input.txt")
	file, err := os.Open("sample.txt")

	if err != nil {
		log.Fatalf("failed to open file: %s", err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	// read file line by line
	for scanner.Scan() {
		line := scanner.Text()

		// first character determine dial rotation direction
		direction := line[0]

		// convert the dial steps to number
		steps, err := strconv.Atoi(line[1:])

		if err != nil {
			log.Fatalf("failed to convert number")
		}

		switch direction {
		case 'L':
			dial = dial - steps
		case 'R':
			dial = dial + steps
		default:
			fmt.Printf("%c\n", direction)
		}

		fmt.Println(line)
		fmt.Println(dial)

		if dial%100 == 0 {
			password++
		}
	}

	fmt.Println("password:", password)

	if err := scanner.Err(); err != nil {
		log.Fatalf("failed to open file: %s", err)
	}
}
