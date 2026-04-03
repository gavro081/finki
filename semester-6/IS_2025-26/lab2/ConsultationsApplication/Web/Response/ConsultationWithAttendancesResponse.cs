using Domain.Models;

namespace Web.Response;

public record ConsultationWithAttendancesResponse(
    Guid Id,
    DateTime StartTime,
    DateTime EndTime,
    Guid RoomId,
    string RoomName,
    List<AttendanceResponse> AttendanceResponses
);