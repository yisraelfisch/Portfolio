import requests
import unittest

BASE_URL = "http://localhost:5000"


class TestFlaskAPI(unittest.TestCase):
    def test_get_all_users(self):
        url = f"{BASE_URL}/user"
        response = requests.get(url)
        self.assertEqual(response.status_code, 200)
        self.assertTrue("data" in response.json())

    def test_get_specific_user(self):
        user_id = 100  # Change this to the desired user ID to test
        url = f"{BASE_URL}/user/{user_id}"
        response = requests.get(url)
        self.assertEqual(response.status_code, 200)
        self.assertTrue("name" in response.json())
        self.assertTrue("surname" in response.json())

    def test_create_user(self):
        url = f"{BASE_URL}/user"
        data = {
            "id": 1000,
            "name": "John",
            "surname": "Doe"
        }
        response = requests.post(url, json=data)
        self.assertEqual(response.status_code, 201)
        self.assertTrue("user_id" in response.json())

    def test_update_user(self):
        user_id = 100  # Change this to the desired user ID to test
        url = f"{BASE_URL}/user/{user_id}"
        data = {
            "name": "Updated Name",
            "surname": "Updated Surname"
        }
        response = requests.put(url, json=data)
        self.assertEqual(response.status_code, 200)
        # Perform additional assertions as needed to verify the update

    def test_delete_user(self):
        user_id = 1000  # Change this to the desired user ID to test
        url = f"{BASE_URL}/user/{user_id}"
        response = requests.delete(url)
        self.assertEqual(response.status_code, 200)
        # Perform additional assertions as needed to verify the deletion


if __name__ == "__main__":
    unittest.main()
