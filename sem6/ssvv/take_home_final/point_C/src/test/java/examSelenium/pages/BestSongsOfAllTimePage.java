package examSelenium.pages;

import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.DefaultUrl;
import net.thucydides.core.pages.PageObject;
import org.openqa.selenium.By;
import org.openqa.selenium.support.FindBy;

@DefaultUrl("https://www.thedelite.com/best-songs-of-all-time-according-to-critics-and-fans")
public class BestSongsOfAllTimePage extends PageObject {
    @FindBy(className = "entry-content")
    private WebElementFacade entryList;

    // README.md specifies that the page contains 100 songs; I only see 50 :<
    static private final int SONG_COUNT = 50;

    public boolean checkIfSongIsGood(String userSongTitle) {
        // <div class="entry_content"> -> [id: <div id="slide_idx">...</div> -> <h2 id="header-slide-idx">...</h2>]
        for(int idx = 1; idx <= SONG_COUNT; idx++) {
            String titleElementId = "header-slide-" + idx;
            String headerText = entryList.findBy(By.id(titleElementId)).getText();
            if (headerText.contains(userSongTitle)) return true;
        }
        return false;
    }
}
