namespace Web.Response;

public record AttendanceResponse(
    Guid Id,
    string UserId,
    string UserName,
    string Status
);