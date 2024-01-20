# My Crappy JSON Library

## Introduction it's stupid but it works...

Your JSON is an instance of the JSON class and represented as a `std::string`, and we use methods to navigate and manipulate it.


## Creating JSON Objects

- **Read from a File**: Utilize the `.readFromFile(std::string src)` method to import JSON data from a file.

- **Create an Empty JSON**: You can create an "empty" JSON (which is essentially a string: `"{\n}"`) using the `createEmptyJson()` method.

- **Import from an Existing String**: If you already have a string, you can import it to create a JSON object with the `.importStringData(std::string content)` method.

Keep in mind that when a JSON object is created, the input data undergoes a thorough check in the constructor. If your JSON is faulty, it gracefully returns an empty JSON.

## Interacting with JSON Objects



- **Retrieve JSON Data**: The `.getData()` method fetches the entire JSON as a string.

- **Get a Value by Key**: For the task of fetching a value based on a key, use the `.getValue(std::string key)` method.

- **Add Data**: Expand your JSON with the `.addData(std::string key, std::string value)` method.

- **Change Data**: Overwrite JSON-data by using the `.changeData(std::string key, std::string value)` method.

- **Save to File**: Use the `.saveFile(std::string src)` method to write your JSON data to an existing file.

