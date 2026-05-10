package pages;

import org.openqa.selenium.By;
import org.openqa.selenium.Keys;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.ui.ExpectedConditions;

import java.util.List;

public class AddUserPage extends BasePage {
    private static final By PAGE_HEADER = By.xpath("//h6[normalize-space()='Add User']");
    private static final By USER_ROLE_DROPDOWN = By.xpath("//label[normalize-space()='User Role']/following::div[contains(@class,'oxd-select-text')][1]");
    private static final By STATUS_DROPDOWN = By.xpath("//label[normalize-space()='Status']/following::div[contains(@class,'oxd-select-text')][1]");
    private static final By DROPDOWN_OPTION = By.cssSelector(".oxd-select-dropdown .oxd-select-option");
    private static final By EMPLOYEE_NAME_INPUT = By.cssSelector("input[placeholder='Type for hints...']");
    private static final By AUTOCOMPLETE_OPTION = By.cssSelector(".oxd-autocomplete-dropdown .oxd-autocomplete-option");
    private static final By USERNAME = By.xpath("//label[normalize-space()='Username']/following::input[1]");
    private static final By PASSWORD = By.xpath("//label[normalize-space()='Password']/following::input[1]");
    private static final By CONFIRM_PASSWORD = By.xpath("//label[normalize-space()='Confirm Password']/following::input[1]");
    private static final By SAVE_BUTTON = By.xpath("//button[normalize-space()='Save']");
    private static final By CANCEL_BUTTON = By.xpath("//button[normalize-space()='Cancel']");
    private static final By FIELD_ERRORS = By.cssSelector(".oxd-input-field-error-message");

    public AddUserPage(WebDriver driver) {
        super(driver);
        waitVisible(PAGE_HEADER);
    }

    public AddUserPage selectUserRole(String role) {
        click(USER_ROLE_DROPDOWN);
        selectDropdownOption(role);
        return this;
    }

    public AddUserPage selectStatus(String status) {
        click(STATUS_DROPDOWN);
        selectDropdownOption(status);
        return this;
    }

    public AddUserPage typeEmployeeName(String hint) {
        WebElement input = waitVisible(EMPLOYEE_NAME_INPUT);
        input.clear();
        input.sendKeys(hint);
        // wait for autocomplete options (and not "Searching...")
        wait.until(d -> {
            List<WebElement> opts = d.findElements(AUTOCOMPLETE_OPTION);
            return !opts.isEmpty()
                    && opts.stream().noneMatch(o -> o.getText().toLowerCase().contains("searching"));
        });
        List<WebElement> options = driver.findElements(AUTOCOMPLETE_OPTION);
        if (options.isEmpty() || options.get(0).getText().toLowerCase().contains("no records")) {
            throw new IllegalStateException("No employee suggestions for hint: " + hint);
        }
        options.get(0).click();
        return this;
    }

    public AddUserPage setUsername(String username) {
        type(USERNAME, username);
        return this;
    }

    public AddUserPage setPassword(String password) {
        type(PASSWORD, password);
        type(CONFIRM_PASSWORD, password);
        return this;
    }

    public AdminUsersPage save() {
        click(SAVE_BUTTON);
        return new AdminUsersPage(driver);
    }

    public AddUserPage saveExpectingErrors() {
        click(SAVE_BUTTON);
        wait.until(ExpectedConditions.visibilityOfElementLocated(FIELD_ERRORS));
        return this;
    }

    public List<String> getValidationErrors() {
        return driver.findElements(FIELD_ERRORS).stream().map(WebElement::getText).toList();
    }

    private void selectDropdownOption(String text) {
        WebElement option = wait.until(d -> {
            for (WebElement o : d.findElements(DROPDOWN_OPTION)) {
                try {
                    if (o.getText().trim().equalsIgnoreCase(text) && o.isDisplayed()) {
                        return o;
                    }
                } catch (Exception ignored) {
                    // option may have gone stale during refresh
                }
            }
            return null;
        });
        option.click();
    }
}
