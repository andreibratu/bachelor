# Selenium Exam

## Problem: My Birthday Song

### Scenario
Please implement the following automated scenario using the Selenium Framework:  
    
   1. The user goes to a page which is able to tell him which song was the most popular on a given day in history (https://playback.fm/birthday-song)
   2. He searches for his birthday song by inputting the corresponding day, month and year of birth.
      * In case you don't want to share your date of birth, you are free to use a random date!
   3. He checks to see if the previously found song can be found among a list of top 100 songs of all time (https://www.thedelite.com/best-songs-of-all-time-according-to-critics-and-fans)
   4. He prints his finding in the console.
   5. He searches for the name of the song on Wikipedia (https://en.wikipedia.org/wiki/Main_Page) and accesses the first link that he finds when performing the search.

The baseline of this scenario can be found under `./src/test/java/examSelenium/stories/MyBirthdaySongStory` but an initial setup is required before running the baseline Story.

### Setup
This is a template project for the exam. 
It provides the base configurations required for running a simple Selenium program. 
Additional steps that are required for the setup will be listed below:
 * Download the WebDriver for Chrome:  https://sites.google.com/a/chromium.org/chromedriver/downloads

 * Provide the path to the driver in the ./serenity.properties file:
 
Linux example:
```$xslt
webdriver.chrome.driver = /usr/lib/chromium-browser/chromedriver
```

Windows example:
```$xslt
webdriver.chrome.driver = C:\\Temp\\drivers\\chromedriver.exe
```

 * Additional Intellij settings, for example:
    * File > Project Structure > Project > Language Level: 8
    * `mvn clean install` in the terminal if dependencies don't show up
    
