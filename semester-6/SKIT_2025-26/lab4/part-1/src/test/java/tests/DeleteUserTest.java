package tests;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import pages.AdminUsersPage;

import java.util.UUID;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

class DeleteUserTest extends BaseTest {

    private static String randomUsername() {
        return "qa_" + UUID.randomUUID().toString().replace("-", "").substring(0, 10);
    }

    @Test
    @DisplayName("Deleting an existing user removes it from the system")
    void deletesExistingUser() {
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
        assertTrue(usersPage.isUserPresent(username), "Precondition: user must exist before delete");

        usersPage.deleteFirstResult();

        usersPage.searchByUsername(username);
        assertFalse(usersPage.isUserPresent(username),
                "User should no longer appear after delete");
    }
}
