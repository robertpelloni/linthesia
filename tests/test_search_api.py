#!/usr/bin/env python3
import unittest
import sys
import os

# Add scripts directory to path to import search_api
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../scripts')))

import search_api

class TestSearchAPI(unittest.TestCase):

    def test_missing_database(self):
        # Temporarily move database if it exists
        db_path = search_api.DB_PATH
        temp_path = db_path + ".bak"

        if os.path.exists(db_path):
            os.rename(db_path, temp_path)

        try:
            result = search_api.search_workspace("test")
            self.assertIn("Error: Index database not found", result)
        finally:
            # Restore database
            if os.path.exists(temp_path):
                os.rename(temp_path, db_path)

    def test_search_results(self):
        # Assumes the database is populated from a previous run
        if os.path.exists(search_api.DB_PATH):
            result = search_api.search_workspace("SheetMusicDisplay")
            self.assertIn("results for", result)

if __name__ == '__main__':
    unittest.main()
