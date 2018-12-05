#include <string>
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

const string GOOGLE_MAPS_API_URL = "https://maps.googleapis.com/maps/api";
const string GEOCODE_API_URL = GOOGLE_MAPS_API_URL + "/geocode/";
const string ELEVATION_API_URL = GOOGLE_MAPS_API_URL + "/elevation/";
const string DISTRANCEMATRIX_API_URL = GOOGLE_MAPS_API_URL + "/distancematrix/";
const string JSON_FORMAT = "json";
const string API_KEY = "UPDATE_WITH_YOUR_API_KEY";

/////////////////////////////////////
// Functions for you to implement. //
/////////////////////////////////////

/**
 * Returns a string with the URL for the reverse geocoding request, according to
 * https://developers.google.com/maps/documentation/geocoding/start#reverse
 *
 * 'latlng' is a string with the latitude and longitude values specifying the
 *   location for which to obtain the closest, human-readable address, in the
 *   format: "latitude,longitude". For example: "33.8824,-117.885".
 */
string buildReverseGeocodeRequestUrl(string latlng);

////////////////////////////////////////////
// End of functions for you to implement. //
////////////////////////////////////////////

//////////////////////////////////////////////////////
// Functions for you to implement for extra credit. //
//////////////////////////////////////////////////////

/**
 * Returns a string with the URL for the elevation request, according to
 * https://developers.google.com/maps/documentation/elevation/start#sample-request
 *
 * 'latlng' is a string with the latitude and longitude values specifying the
 *   location for which to obtain the closest, human-readable address, in the
 *   format: "latitude,longitude". For example: "33.8824,-117.885".
 */
string buildElevationRequestUrl(string latlng); // Extra credit 1

/**
 * Returns a float with the conversion from meters to feet.
 */
float convertToFeet(float meters); // Extra credit 1

/**
 * Returns a string with the URL for the distance matrix request, according to
 * https://developers.google.com/maps/documentation/distance-matrix/start#sample-request
 *
 * 'units' is a string specifying the unit system to use when expressing
 *   distance as text. For this assignment, it must be set to "imperial".
 * 'origin' is a string containing the origin address. For example:
 *   "800 N State College Blvd, Fullerton, CA 92831".
 * 'destination' is a string containing the destination address. For example:
 *   "1600 Amphitheatre Parkway, Mountain View, CA 94043".
 */
string buildDistanceMatrixRequest(string units, string origin,
                                  string destination); // Extra credit 2

/////////////////////////////////////////////////////////////
// End of functions for you to implement for extra credit. //
/////////////////////////////////////////////////////////////

/////////////////////////
// Functions provided. //
/////////////////////////

/**
 * Returns a string with the URL for the geocoding request, according to
 * https://developers.google.com/maps/documentation/geocoding/start#geocoding-request-and-response-latitudelongitude-lookup
 *
 * 'address' is a string containing the origin address. For example:
 *   "800 N State College Blvd, Fullerton, CA 92831".
 */
string buildGeocodeRequestUrl(string address);

/**
 * Returns a new string with the whitespaces replaced with the plus symbol
 * char ('+').
 */
string formatAddressUrlSafe(string address);

/**
 * Returns a tuple of two elements where the first element is the latitude of
 * the geolocation as a float, and the second element is the longitude of the
 * geolocation as a float.
 *
 * If the input is invalid, it returns the tuple {0.0f, 0.0f}.
 */
tuple<float, float> getGeolocation(string geocodingResponseMessage);

/**
 * Returns a tuple of two elements where the first element is a string with the
 * distance, and the second element is a string with the duration.
 *
 * If the input is invalid, it returns the tuple {"", ""}.
 */
tuple<string, string> getDistanceAndDuration(
  string distanceMatrixResponseMessage);

/**
 * Returns the address from the response message as a string.
 *
 * If the input is invalid, it returns an empty string.
 */
string getAddress(string reverseGeocodingResponseMessage);

/**
 * Returns the elevation from the response message as a float.
 *
 * If the input is invalid, it returns 0.0f.
 */
float getElevation(string locationResponseMessage);

/**
 * Function called by the CURL object to process the response data through the
 * CURLOPT_WRITEFUNCTION option.
 */
size_t CurlWrite_CallbackFunc_StdString(
  void *contents, size_t size, size_t nmemb, std::string *s);

////////////////////////////////
// End of functions provided. //
////////////////////////////////


int main() {
  // These inputs below are hard-coded as an example. You will need to replace
  // them so that you ask the user of the program to input them instead.
  string address = "800 N State College Blvd, Fullerton, CA 92831";

  // This is the URL that the program will call to contact the Google Maps API
  // server with the request.
  string url = buildGeocodeRequestUrl(address);

  // Instantiate the objects used to make the HTTP request call and to store the
  // response code and response message.
  CURL *curl;
  CURLcode responseCode;
  string responseMessage;

  // Initialize the CURL object, used to make the HTTP calls.
  curl = curl_easy_init();
  if (curl) {
    // Set the URL to make the HTTP call.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    // Set the function that will take care of handling the response from the
    // HTTP call.
    curl_easy_setopt(
      curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
    // Indicate the string where the response data will be stored.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseMessage);

    // Perform the call and store the response code.
    responseCode = curl_easy_perform(curl);

    // Check if the call was successful. If not, print out an error and quit the
    // program.
    if(responseCode != CURLE_OK) {
      cout << "curl_easy_perform() failed: ";
      cout << curl_easy_strerror(responseCode) << endl;
      exit(1);
    }

    // Process the response message and print out the location.
    tuple<float, float> location = getGeolocation(responseMessage);
    float latitude = get<0>(location);
    float longitude = get<1>(location);
    cout << "Location: (" << latitude << ", " << longitude << ")" << endl;

    // Clean up and close all streams used for CURL.
    curl_easy_cleanup(curl);
  } else {
    cout << "There was an error initializing cURL" << endl;
    exit(1);
  }

  return 0;
}

string buildGeocodeRequestUrl(string address) {
  string url = GEOCODE_API_URL + JSON_FORMAT;
  url += "?address=" + formatAddressUrlSafe(address);
  url += "&key=" + API_KEY;
  return url;
}

string buildReverseGeocodeRequestUrl(string latlng) {
  // TODO(you): Implement for extra credit.
  return "";
}

string buildElevationRequestUrl(string latlng) {
  // TODO(you): Implement for extra credit.
  return "";
}

string buildDistanceMatrixRequest(
  string units, string origin, string destination) {
    // TODO(you): Implement for extra credit.
    return "";
}

string formatAddressUrlSafe(string address) {
  string urlSafeAddress;
  for(int i = 0; i < address.length(); i++) {
    if (address.at(i) == ' ') {
      urlSafeAddress.push_back('+');
    } else {
      urlSafeAddress.push_back(address.at(i));
    }
  }
  return urlSafeAddress;
}

tuple<float, float> getGeolocation(string geocodingResponseMessage) {
  json geocodingResponseJson = json::parse(geocodingResponseMessage);
  if (geocodingResponseJson.find("results") != geocodingResponseJson.end()) {
    json firstResult = geocodingResponseJson["results"][0];
    if (firstResult.find("geometry") != firstResult.end()) {
      json geometry = firstResult["geometry"];
      if (geometry.find("location") != geometry.end()) {
        json location = geometry["location"];
        return make_tuple(location["lat"], location["lng"]);
      }
    }
  }
  return make_tuple(0.0f, 0.0f);
}

string getAddress(string reverseGeocodingResponseMessage) {
  json reverseGeocodingResponseJson =
      json::parse(reverseGeocodingResponseMessage);
  if (reverseGeocodingResponseJson.find("results") != reverseGeocodingResponseJson.end()) {
    json firstResult = reverseGeocodingResponseJson["results"][0];
    if (firstResult.find("formatted_address") != firstResult.end()) {
      return firstResult["formatted_address"];
    }
  }
  return "";
}

float getElevation(string locationResponseMessage) {
  json locationResponseJson = json::parse(locationResponseMessage);
  if (locationResponseJson.find("results") != locationResponseJson.end()) {
    json firstResult = locationResponseJson["results"][0];
    if (firstResult.find("elevation") != firstResult.end()) {
      return firstResult["elevation"];
    }
  }
  return 0.0f;
}

tuple<string, string> getDistanceAndDuration(
  string distanceMatrixResponseMessage) {
  json distanceMatrixResponseJson = json::parse(distanceMatrixResponseMessage);
  if (distanceMatrixResponseJson.find("rows") != distanceMatrixResponseJson.end()) {
    json firstRow = distanceMatrixResponseJson["rows"][0];
    if (firstRow.find("elements") != firstRow.end()) {
      json firstElement = firstRow["elements"][0];
      string distanceText = firstElement["distance"]["text"];
      string durationText = firstElement["duration"]["text"];
      return make_tuple(distanceText, durationText);
    }
  }
  return make_tuple("", "");
}

size_t CurlWrite_CallbackFunc_StdString(
  void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e) {
        //handle memory problem
        return 0;
    }
    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}
