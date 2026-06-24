package main

import (
	"log"
	"os/exec"
	"strings"

	"github.com/gofiber/fiber/v2"
)

// SubmoduleStatus represents the state of a single git submodule
type SubmoduleStatus struct {
	Path   string `json:"path"`
	Commit string `json:"commit"`
	Status string `json:"status"` // clean, dirty, out-of-sync
}

// CheckSubmodules retrieves the status of all git submodules
func CheckSubmodules() ([]SubmoduleStatus, error) {
	cmd := exec.Command("git", "submodule", "status")
	out, err := cmd.CombinedOutput()
	if err != nil {
		log.Printf("Error checking submodules: %v\n", err)
		return nil, err
	}

	lines := strings.Split(string(out), "\n")
	var statuses []SubmoduleStatus

	for _, line := range lines {
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}

		parts := strings.Fields(line)
		if len(parts) >= 2 {
			statusFlag := "clean"
			if strings.HasPrefix(line, "+") {
				statusFlag = "out-of-sync"
			} else if strings.HasPrefix(line, "U") {
				statusFlag = "dirty" // Merge conflict
			}

			// Extract hash, removing prefix modifiers (+ or - or U)
			hash := parts[0]
			if len(hash) > 0 && (hash[0] == '+' || hash[0] == '-' || hash[0] == 'U') {
				hash = hash[1:]
			}

			statuses = append(statuses, SubmoduleStatus{
				Path:   parts[1],
				Commit: hash,
				Status: statusFlag,
			})
		}
	}

	return statuses, nil
}

// SubmoduleStatusHandler exposes the submodule status via HTTP JSON
func SubmoduleStatusHandler(c *fiber.Ctx) error {
	statuses, err := CheckSubmodules()
	if err != nil {
		return c.Status(500).JSON(fiber.Map{
			"error": "Failed to check submodules",
		})
	}

	return c.JSON(statuses)
}
