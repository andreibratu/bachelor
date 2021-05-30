package examSelenium.pages;

import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.DefaultUrl;
import net.thucydides.core.pages.PageObject;
import org.openqa.selenium.support.FindBy;

@DefaultUrl("https://en.wikipedia.org/wiki/Main_Page")
public class WikipediaPage extends PageObject {
    @FindBy(id = "searchInput")
    private WebElementFacade searchInput;

    public void lookUpBirthdaySong(String userSongName) {
        searchInput.type(userSongName);
        searchInput.submit();
    }
}
