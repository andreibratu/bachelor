package examSelenium.steps;

import examSelenium.pages.BestSongsOfAllTimePage;
import examSelenium.pages.BirthdaySongPage;
import examSelenium.pages.WikipediaPage;
import net.thucydides.core.annotations.Step;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.hasItem;

public class EndUserSteps {

    BirthdaySongPage birthdaySongPage;
    BestSongsOfAllTimePage bestSongsOfAllTimePage;
    WikipediaPage wikipediaPage;

    @Step
    public void openBirthdaySongsPage() {
        birthdaySongPage.open();
    }

    @Step
    public String[] searchSong() {
        return birthdaySongPage.searchBirthdaySong("16", "June", "1999");
    }

    @Step
    public void openBestSongsOfAllTimePage() {
        bestSongsOfAllTimePage.open();
    }

    @Step
    public boolean lookUpBestSongsAllTime(String userSongTitle) {
        return bestSongsOfAllTimePage.checkIfSongIsGood(userSongTitle);
    }

    @Step
    public void openWikipediaPage() {
        wikipediaPage.open();
    }

    @Step
    public void lookUpBirthdaySong(String name) {
        wikipediaPage.lookUpBirthdaySong(name);
    }

}
