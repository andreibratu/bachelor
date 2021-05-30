package examSelenium.pages;

import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.DefaultUrl;

import net.thucydides.core.pages.PageObject;
import org.openqa.selenium.By;
import org.openqa.selenium.support.FindBy;

@DefaultUrl("https://playback.fm/birthday-song")
public class BirthdaySongPage extends PageObject {
    @FindBy(id="day")
    private WebElementFacade daySelect;

    @FindBy(id="month")
    private WebElementFacade monthSelect;

    @FindBy(id="year")
    private WebElementFacade yearSelect;

    @FindBy(className="findSong")
    private WebElementFacade findSongButton;

    @FindBy(id = "id01")
    private WebElementFacade resultContainer;

    public String[] searchBirthdaySong(String day, String month, String year) {
        daySelect.selectByVisibleText(day);
        monthSelect.selectByVisibleText(month);
        yearSelect.selectByVisibleText(year);
        findSongButton.click();
        waitABit(1000 * 3);
        String songArtist = resultContainer.find(By.tagName("strong")).getText();
        // Split string into song title and song artist
        return songArtist.split(" by ");
    }
}
