using Domain.Dto;
using Domain.Models;
using Web.Request;
using Web.Response;

namespace Web.Extensions;

public static class AttendanceExtensions
{
    public static AttendanceResponse ToResponse(this Attendance attendance)
    {
        return new AttendanceResponse(
            Comment : attendance.Comment,
            FirstName : attendance.User.FirstName,
            LastName : attendance.User.LastName,
            Status : attendance.Status.ToString(),
            UserId : attendance.UserId
        );
    }

    public static List<AttendanceResponse> ToResponse(this List<Attendance> attendances)
    {
        return attendances.Select(x => x.ToResponse()).ToList();
    }
    
    public static AttendanceDto ToDto(this AttendanceRequest request)
    {
        return new AttendanceDto
        {
            UserId = request.UserId,
            Comment = request.Comment,
            ConsultationId = request.ConsultationId,
            RoomId = request.RoomId
        };
    }
    
    public static BasicAttendanceResponse ToBasicResponse(this Attendance attendance)
    {
        return new BasicAttendanceResponse(
            Id : attendance.Id,
            FirstName : attendance.User.FirstName,
            LastName: attendance.User.LastName
        );
    }
}