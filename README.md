# CPSC 120 - Project

## Goals

The objective of this project is to write a program that can talk to the Google Maps API.

## Background

## API

API stands for Application Programming Interface, and it is a topic you will learn in later computer science courses. In summary, an API is a software intermediary that allows two applications to talk to each other. In the industry, people refer to an API as the service provided by programs running in servers that can be called by any program, website, app, etc.

In this project, your program will talk to the Google Maps API which is hosted in Google's servers, and it can be called through the internet using HTTP requests.

You can read more about [APIs](https://en.wikipedia.org/wiki/Application_programming_interface) and about [HTTP requests](https://www.codecademy.com/articles/http-requests).

## Google Maps API

The [Google Maps API](https://developers.google.com/maps/documentation/) is a collection of API services that Google provides for anyone to use. In this project, we will be using the [Geocoding API](https://developers.google.com/maps/documentation/geocoding/start). For the extra credits, we will also be using the [Elevation API](https://developers.google.com/maps/documentation/elevation/start), and the [Distance Matrix API](https://developers.google.com/maps/documentation/distance-matrix/start).

### API key

Although there are some APIs out there that are free to use, most APIs charge you for their usage (for example, they might charge you $0.0001 every time you send a request to the API). A way to identify the person or organization to charge for the usage, the API service can provide you an API key, which is used to identify which person or organization to charge. Every time you call the API, you have to attach your API key to the request.

For this project, I will provide you with an API key that will stop working at some point in January. After that, if you want to obtain an API key, you can do so by creating your own Google Cloud project and configuring your own API key. You might be able to receive free credit using the education program for Google Cloud: https://cloud.google.com/edu/

Organizations on campus like [ACM](http://acm.ecs.fullerton.edu/) are familiar with Google Cloud, so you can always approach them to get help in case you want to continue working on your project and need to set up a Google Cloud project to obtain an API key.

## Tuples

As you have learned in class, a function either does not return anything (`void`), or returns **one** value. In some cases, you might want a function that returns two or more values.

For example, let's imagine that we have a function that takes two strings, one for first name, and one for last name, and then it returns one single string in the format "last name, first name". The function might look like this:

```cpp
string buildFormalName(string firstName, string lastName) {
  string formalName = lastName + ", " + firstName;
  return formalName;
}
```

Now, let's imagine we want to do the opposite, and we want to take as an input the formal name (one single string), but return the first name and the last name as two separate strings. Because functions only allow you to return one value, one solution for this problem is to use an [`std::tuple`](https://en.cppreference.com/w/cpp/utility/tuple).

A `tuple` is a fixed-sized collection of values. These values do not necessarily have to be of the same type (as it is in the case of an array). Here is how we would use a tuple to solve the problem above:

```cpp
std::tuple<std::string, std::string> getFirstAndLastName(std::string formal) {
  int positionOfComma = formal.find(',');
  std::string lastName = formal.substr(0, positionOfComma);
  std::string firstName = formal.substr(positionOfComma + 2);

  return std::make_tuple(firstName,lastName);
}
```

Here is another example of how to declare and use a tuple:

```cpp
std::tuple<std::string, char, int> person = std::make_tuple("Luis", 'L', 27);

std::cout << "First name:        " << std::get<0>(person) << std::endl;
std::cout << "Last name initial: " << std::get<1>(person) << std::endl;
std::cout << "Age:               " << std::get<2>(person) << std::endl;

int age = std::get<2>(person);
if (age < 18) {
  std::cout << "The person is a minor." << std::endl;
} else {
  std::cout << "The person is an adult." << std::endl;
}
```

## Safe URLs

URLs such as `https://www.google.com/` cannot contain spaces. Therefore, a URL that does not have spaces or invalid characters is considered a *safe* URL.

Because the URLs used to call the Google Maps API contain physical mailing addresses, we need to make sure that there are no spaces in the addresses. The convention that the Google Maps API uses is to replace the spaces in an address with a plus symbol (`+`). A function that takes care of converting an address with spaces to an address using the `+` symbol has been provided to you in the program (see the `formatAddressUrlSafe` function).

## External libraries

### libcurl

[libcurl](https://curl.haxx.se/libcurl/) is a library that allow C++ programs to make HTTP requests (in addition to many other types of requests). This library is not installed in your Tuffix machine, therefore you will have to run the following commands to install it:

```
$ sudo apt-get install libcurl4-gnutls-dev
```

You might get the following error if you are running Tuffix on a VM:

```
E:dpkg was interrupted, you must manually run 'sudo dpkg -- configure -a' to correct the problem
```

In that case, run `sudo dpkg -- configure -a` first and then try the command above again.

When running `sudo` commands, the terminal might ask you for your password. If you are using the Tuffix distribution through a virtual machine, the password for your account is `student`. If you installed your own Tuffix machine, use the password for your account.

Once installed, `g++` needs to know that you want to include this library when compiling code that uses it. Therefore, you will need to pass an additional flag: `-lcurl`.

For example, when building the program for this project, you would run `g++ project.cpp -lcurl -o project`.

### json

[JSON](https://en.wikipedia.org/wiki/JSON), which stands for JavaScript Object Notation, is a file format used to store structured data. Some APIs like the Google Maps API return the requested data in JSON format. Because of that, we have to use a library that can read data in JSON format and parse it in an object that makes is easier for us to read in C++.

Your Tuffix machines already have the `<nlohmann/json.hpp>` library installed, which is an open-source project that you can find in https://github.com/nlohmann/json

To simply use this library, you just need to include it in your program:

```cpp
#include <nlohmann/json.hpp>
```

In the same way you use `using namespace std;` to avoid typing the prefix `std::` in your program, you can use `using json = nlohmann::json;` to avoid typing the prefix `nlohmann::`:

```cpp
#include <nlohmann/json.hpp>

using json = nlohmann::json;
```

You will not have to write any code using this library as the code that handles the JSON objects is already provided to you.

## Instructions

### Updating the API key and compiling the program

A file `project.cpp` has been provided to you. This file already has working code that calls the API. However, the first step for you to do is to update the API key with the one provided to you by your instructor.

Once the `API_KEY` variable has been updated, compile your code with the following command:

```
$ g++ project.cpp -lcurl -o project
```

Make sure you have installed the `libcurl` library as explained in the instructions on the background section. Otherwise, you might see the following error:

```
fatal error: curl/curl.h: No such file or directory
#include <curl/curl.h>
         ^~~~~~~~~~~~~
compilation terminated.
```

### Running the program

Once the program compiles successfully, run the program. If the program works perfectly, it should print out the GPS coordinates of the university:

```
$ ./project
Location: (33.8824, -117.885)
```

### Updating the program

The code provided to you takes care of converting a physical mailing address to its corresponding geolocations (coordinates) using the [Geocoding API](https://developers.google.com/maps/documentation/geocoding/start).

In this project, you will do the following:
* Allow user to input any address instead of using the hardcoded address.
* Add the functionality for [reverse geocoding](https://developers.google.com/maps/documentation/geocoding/start#reverse).
* Provide a menu for the user to select what action they want to take and accept the corresponding input.

The program **must** look like this:

```
$ ./project
[1] Convert an address to GPS coordinates
[2] Convert GPS coordinates to an address
[0] Quit the program

Enter an option: 1
Enter an address: 800 N State College Blvd, Fullerton, CA 92831
The GPS coordinates are: (33.8824, -117.885)
```

```
$ ./project
[1] Convert an address to GPS coordinates
[2] Convert GPS coordinates to an address
[0] Quit the program

Enter an option: 2
Enter the latitude: 33.8824
Enter the longitude: -117.885
The address is: 800 N State College Blvd, Fullerton, CA 92831, USA
```

```
$ ./project
[1] Convert an address to GPS coordinates
[2] Convert GPS coordinates to an address
[0] Quit the program

Enter an option: 0
Bye!
```

```
$ ./project
[1] Convert an address to GPS coordinates
[2] Convert GPS coordinates to an address
[0] Quit the program

Enter an option: 5
That's an invalid option! Try again.

[1] Convert an address to GPS coordinates
[2] Convert GPS coordinates to an address
[0] Quit the program

Enter an option: 0
Bye!
```

Note that if the user enters a valid option, the program should end once the corresponding output is displayed. It should not show the menu again unless the user inputted an invalid option.

## Extra credit

*Note: if you do both extra credits, update the menu option numbers accordingly.*

### Option 1: Elevation API (+40 points)

Add an option to get the elevation of a given geolocation. For this option, you will use the [Distance Matrix API](https://developers.google.com/maps/documentation/distance-matrix/start). You will need to implement the `buildDistanceMatrixRequest()` function and use the `getDistanceAndDuration()` to parse the response message.

```
$ ./project
[1] Convert an address to GPS coordinates
[2] Convert GPS coordinates to an address
[3] Get the elevation of a geolocation (GPS coordinates)
[0] Quit the program

Enter an option: 3
Enter the latitude: 33.8824
Enter the longitude: -117.885
Elevation: 246.28 ft.
```

### Option 2: Distance Matrix API (+40 points)

Add an option to get the distance and duration of a trip to go from one address to another. For this option, you will use the [Elevation API](https://developers.google.com/maps/documentation/elevation/start). You will need to implement the `buildElevationRequestUrl()` and `convertToFeet()` functions, and use the `getElevation()` to parse the response message.

```
$ ./project
[1] Convert an address to GPS coordinates
[2] Convert GPS coordinates to an address
[3] Get distance and duration to go from one address to another address
[0] Quit the program

Enter an option: 3
Enter the origin address: 800 N State College Blvd, Fullerton, CA 92831
Enter the destination address: 1600 Amphitheatre Parkway, Mountain View, CA 94043
Distance: 391 mi
Duration: 6 hours 2 mins
```

## Grading

**IMPORTANT: If the file `program.cpp` does not compile in Tuffix, you will receive a score of 0 for the project.**

For this project, you only need to modify the file `project.cpp`. There is no requirement on submitting a `README.md` file, nor a `ls.out` file.

* Menu implemented: 10 points
* Menu is displayed again if user enters invalid option: 10 points
* Menu handles incorrect invalid input: 10 points
* API key updated and "Convert an address to GPS coordinates" feature works: 20 points
* "Convert GPS coordinates to an address" feature: 50 points

Total: 100 points

## Deadline

Repositories will be graded with commits that were submitted **no later than Friday, December 21st, 2018 at 11:59:59pm PST**. Any commits pushed after that deadline will be ignored when grading the project.
