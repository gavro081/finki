namespace Web.Response;

public record ConsultationsResponse(
    Guid Id,
    DateOnly Date,
    Guid RoomId,
    int RegisteredStudents,
    List<BasicAttendanceResponse> Attendances
); 