package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Println("Starting Jules Autopilot Backend...")

	// Start Shadow Pilot background daemon
	go func() {
		for {
			MonitorGitDiff()
			time.Sleep(10 * time.Second) // Poll every 10 seconds for testing
		}
	}()

	// Block main thread
	select {}
}
