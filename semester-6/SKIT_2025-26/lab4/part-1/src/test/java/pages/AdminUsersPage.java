package pages;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.ui.ExpectedConditions;

import java.util.List;

public class AdminUsersPage extends BasePage {
    private static final By PAGE_HEADER = By.xpath("//h5[normalize-space()='System Users']");
    private static final By ADD_BUTTON = By.xpath("//button[normalize-space()='Add']");
    private static final By USERNAME_FILTER = By.xpath("//label[normalize-space()='Username']/following::input[1]");
    private static final By SEARCH_BUTTON = By.xpath("//button[normalize-space()='Search']");
    private static final By RESULT_ROWS = By.cssSelector(".oxd-table-card");
    private static final By RECORDS_FOUND = By.cssSelector(".orangehrm-horizontal-padding .oxd-text--span");
    private static final By NO_RECORDS = By.xpath("//span[normalize-space()='No Records Found']");
    private static final By CONFIRM_DELETE = By.xpath("//button[contains(@class,'oxd-button') and contains(.,'Yes')]");
    private static final By TOAST = By.cssSelector(".oxd-toast");

    public AdminUsersPage(WebDriver driver) {
        super(driver);
        waitVisible(PAGE_HEADER);
    }

    public AddUserPage clickAdd() {
        click(ADD_BUTTON);
        return new AddUserPage(driver);
    }

    public AdminUsersPage searchByUsername(String username) {
        dismissToast();
        type(USERNAME_FILTER, username);
        click(SEARCH_BUTTON);
        wait.until(d -> {
            List<WebElement> rows = d.findElements(RESULT_ROWS);
            List<WebElement> empty = d.findElements(NO_RECORDS);
            return !rows.isEmpty() || !empty.isEmpty();
        });
        return this;
    }

    public boolean isUserPresent(String username) {
        return driver.findElements(By.xpath(
                "//div[contains(@class,'oxd-table-card')]//div[normalize-space()='" + username + "']"
        )).size() > 0;
    }

    public AdminUsersPage deleteFirstResult() {
        WebElement trash = waitClickable(By.cssSelector(".oxd-table-card .bi-trash"));
        trash.click();
        click(CONFIRM_DELETE);
        wait.until(ExpectedConditions.invisibilityOfElementLocated(CONFIRM_DELETE));
        return this;
    }

    private void dismissToast() {
        List<WebElement> toasts = driver.findElements(TOAST);
        if (!toasts.isEmpty()) {
            wait.until(ExpectedConditions.invisibilityOfElementLocated(TOAST));
        }
    }
}
