using Domain.Dto;
using Domain.Models;
using Web.Request;
using Web.Response;

namespace Web.Extensions;

public static class ConsultationMappingExtensions 
{
    public static ConsultationResponse ToResponse(this Consultation cons)
    {
        return new ConsultationResponse(
            Id: cons.Id,
            StartTime: cons.StartTime,
            EndTime: cons.EndTime,
            RoomId: cons.RoomId,
            RoomName: cons.Room?.Name // mora za da ne padne,
        );
    }
    
    public static ConsultationWithAttendancesResponse ToResponseWithAttendance(this Consultation cons)
    {
        return new ConsultationWithAttendancesResponse(
            Id: cons.Id,
            StartTime: cons.StartTime,
            EndTime: cons.EndTime,
            RoomId: cons.RoomId,
            RoomName: cons.Room?.Name,
            AttendanceResponses: cons.Attendances?.ToList()?.ToResponse() ?? new List<AttendanceResponse>()
        );
    }
    
    public static List<ConsultationResponse> ToResponse(this List<Consultation> cons)
    {
        return cons.Select(x => x.ToResponse()).ToList();
    }

    public static ConsultationDto ToDto(this ConsultationRequest request)
    {
        return new ConsultationDto
        {
            EndTime = request.EndTime,
            StartTime = request.StartTime,
            RoomId = request.RoomId
        };
    }
    
}