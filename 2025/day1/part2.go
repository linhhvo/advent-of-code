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

	file, err := os.Open("input.txt")
	// file, err := os.Open("sample.txt")

	if err != nil {
		log.Fatalf("failed to open file: %s", err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	// read file line by line
	for scanner.Scan() {
		line := scanner.Text()

		fmt.Println(line)

		// first character determine dial rotation direction
		direction := line[0]

		// convert the dial steps to number
		steps, err := strconv.Atoi(line[1:])

		if err != nil {
			log.Fatalf("failed to convert number")
		}

		// add how many times dial makes a full rotation
		fullCount := steps / 100
		password = password + fullCount

		// use remainder to check if dial passes 0 for the final rotation
		remainder := steps % 100

		switch direction {
		case 'L':
			// passes 0 when, for example, rotate L10 when dial is at 5
			if dial != 0 && dial < remainder {
				password++
			}

			dial = dial - remainder

			// calculate the actual dial number
			if dial < 0 {
				dial = dial + 100
			}

		case 'R':
			// passes 0 when, for example, rotate R10 when dial is at 95
			if dial != 0 && (100-dial) < remainder {
				password++
			}

			dial = dial + remainder

			// calculate the actual dial number
			if dial > 99 {
				dial = dial - 100
			}

		default:
			fmt.Printf("%c\n", direction)
		}

		// if dial points to 0 after rotation
		if dial%100 == 0 {
			password++
		}
	}

	fmt.Println("password:", password)

	if err := scanner.Err(); err != nil {
		log.Fatalf("failed to open file: %s", err)
	}
}
