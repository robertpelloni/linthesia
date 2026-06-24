package main

import (
	"fmt"
	"log"
	"time"

	"github.com/gofiber/fiber/v2"
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

	app := fiber.New()

	app.Get("/system/status/submodules", SubmoduleStatusHandler)

	log.Fatal(app.Listen(":8080"))
}
