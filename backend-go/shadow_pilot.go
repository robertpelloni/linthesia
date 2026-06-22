package main

import (
	"fmt"
	"log"
	"os/exec"
	"strings"
)

// MonitorGitDiff checks for changes in the working directory that might indicate anomalies.
func MonitorGitDiff() (string, error) {
	cmd := exec.Command("git", "diff")
	out, err := cmd.CombinedOutput()
	if err != nil {
		log.Printf("Error running git diff: %v\n", err)
		return "", err
	}

	diffStr := string(out)
	if strings.TrimSpace(diffStr) == "" {
		fmt.Println("No anomalies detected by Shadow Pilot (working tree clean).")
		return "", nil
	}

	fmt.Println("Shadow Pilot detected anomalies (uncommitted changes):")
	fmt.Println(diffStr)

	// Trigger CI Auto-Fix to attempt to resolve the anomaly
	TriggerCIAutoFix()
	// TODO: Add logic to send this diff to an LLM or logging system

	return diffStr, nil
}
