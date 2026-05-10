package pages;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;

public class DashboardPage extends BasePage {
    private static final By TOPBAR_HEADER = By.cssSelector("h6.oxd-topbar-header-breadcrumb-module");
    private static final By ADMIN_MENU = By.xpath("//a[contains(@href,'/admin/viewSystemUsers') or .//span[normalize-space()='Admin']]");

    public DashboardPage(WebDriver driver) {
        super(driver);
        waitVisible(TOPBAR_HEADER);
    }

    public AdminUsersPage openAdmin() {
        click(ADMIN_MENU);
        return new AdminUsersPage(driver);
    }
}
