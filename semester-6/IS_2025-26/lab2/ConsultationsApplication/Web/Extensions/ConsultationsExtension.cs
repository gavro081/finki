using Domain.Dto;
using Domain.Models;
using Web.Request;
using Web.Response;

namespace Web.Extensions;

public static class ConsultationMappingExtensions 
{
    public static ConsultationResponse? ToResponse(this Consultation c)
    {
        return new ConsultationResponse(
            c.Id,
            c.StartTime,
            c.EndTime,
            c.RoomId,
            c.Room?.Name
        );
    }

    public static ConsultationWithAttendancesResponse? ToResponseWithAttendances(this Consultation c)
    {
        var res = c.Attendances.ToList().ToResponse();

        return new ConsultationWithAttendancesResponse(
            c.Id, c.StartTime, c.EndTime, c.RoomId, c.Room?.Name, res
        );
    }
    
    public static List<ConsultationResponse> ToResponse(this List<Consultation> consultations)
    {
        return consultations.Select(x => x.ToResponse()).ToList();
    }

    public static ConsultationDto toDto(this ConsultationRequest request)
    {
        return new ConsultationDto
        {
            StartTime = request.StartTime,
            EndTime = request.EndTime,
            RoomId = request.RoomId
        };
    }
    
}