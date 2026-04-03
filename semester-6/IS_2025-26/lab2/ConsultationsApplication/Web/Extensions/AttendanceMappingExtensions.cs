using Domain.Models;
using Web.Response;

namespace Web.Extensions;

public static class AttendanceMappingExtensions
{
    public static AttendanceResponse? ToResponse(this Attendance c)
    {
        return new AttendanceResponse(
            c.Id,
            c.UserId,
            c.User.FirstName + " " + c.User.LastName,
            c.Status.ToString()
        );
    }
    // List<Attendance> -> List<AttendanceResponse>   
    public static List<AttendanceResponse> ToResponse(this List<Attendance> atts)
    {
        // return consultations.Select(x => x.ToResponse()).ToList();
        return atts.Select(x => x.ToResponse()).ToList();
    }
}