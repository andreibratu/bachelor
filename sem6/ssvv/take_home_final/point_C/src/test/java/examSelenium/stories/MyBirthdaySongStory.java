package examSelenium.stories;

import net.serenitybdd.junit.runners.SerenityRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

import examSelenium.steps.EndUserSteps;

import java.util.concurrent.TimeUnit;

@RunWith(SerenityRunner.class)
public class MyBirthdaySongStory {

    private static final int SECONDS_TO_KEEP_PAGE_OPEN = 10;

    @Managed(uniqueSession = true)
    public WebDriver webdriver;

    @Steps
    public EndUserSteps student;

    @Test
    public void searchingForMyBirthdaySong() {

        student.openBirthdaySongsPage();

        String[] songMeta = student.searchSong();

        // They open the article with the top 100 songs of all time
        student.openBestSongsOfAllTimePage();

        // They check if his songs is in the top (simply tries to match the full name)
        // and then prints the appropriate message in the console
        boolean isSongDecent = student.lookUpBestSongsAllTime(songMeta[0]);
        if (isSongDecent) {
            System.out.println(songMeta[0] + " by " + songMeta[1] + " is one of the best songs of all time!");
        }
        else {
            System.out.println(songMeta[0] + " by " + songMeta[1] + " is pretty nice!");
        }

        // They go on Wikipedia
        student.openWikipediaPage();

        // They search for the song there as well and opens the first result
        student.lookUpBirthdaySong(songMeta[0]);

        // They keep the page open al little longer after the process is over
        waitForIt(SECONDS_TO_KEEP_PAGE_OPEN);
    }

    private void waitForIt(int secondsToWait)
    {
        try {
            TimeUnit.SECONDS.sleep(secondsToWait);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



}
