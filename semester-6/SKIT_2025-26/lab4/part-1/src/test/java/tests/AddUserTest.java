package tests;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import pages.AddUserPage;
import pages.AdminUsersPage;

import java.util.List;
import java.util.UUID;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

class AddUserTest extends BaseTest {

    private static String randomUsername() {
        return "qa_" + UUID.randomUUID().toString().replace("-", "").substring(0, 10);
    }

    @Test
    @DisplayName("Adding a user with valid data persists the user in the system")
    void addsUserWithValidData() {
        String username = randomUsername();

        AdminUsersPage usersPage = loginAsAdmin().openAdmin()
                .clickAdd()
                .selectUserRole("ESS")
                .selectStatus("Enabled")
                .typeEmployeeName("a")
                .setUsername(username)
                .setPassword("Password123!")
                .save();

        usersPage.searchByUsername(username);
        assertTrue(usersPage.isUserPresent(username),
                "Newly created user should appear in the search results");

        // cleanup
        usersPage.deleteFirstResult();
    }

    @Test
    @DisplayName("Saving the form with empty mandatory fields shows validation errors")
    void rejectsEmptyMandatoryFields() {
        AddUserPage addUserPage = loginAsAdmin().openAdmin()
                .clickAdd()
                .saveExpectingErrors();

        List<String> errors = addUserPage.getValidationErrors();
        assertFalse(errors.isEmpty(), "Form should report validation errors for empty fields");
        assertTrue(errors.stream().anyMatch(e -> e.toLowerCase().contains("required")),
                "At least one error should mention required field, got: " + errors);
    }
}
