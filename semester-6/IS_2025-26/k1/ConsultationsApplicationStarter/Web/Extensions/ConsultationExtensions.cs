using Domain.Models;
using Web.Response;

namespace Web.Extensions;

public static class ConsultationExtensions
{
    public static ConsultationsResponse ToResponse(this Consultation consultation)
    {
        return new ConsultationsResponse(
            Id: consultation.Id,
            RoomId: consultation.RoomId,
            Date: DateOnly.FromDateTime(consultation.StartTime),
            RegisteredStudents: consultation.RegisteredStudents,
            Attendances: consultation.Attendances.Select(x => x.ToBasicResponse()).ToList()
        );
    }

    public static List<ConsultationsResponse> ToResponse(this List<Consultation> list)
    {
        return list.Select(x => x.ToResponse()).ToList();
    }

    public static BasicConsultationsResponse ToBasicResponse(this Consultation consultation)
    {
        return new BasicConsultationsResponse(
            Id: consultation.Id,
            RoomId: consultation.RoomId,
            Start: consultation.StartTime,
            End: consultation.EndTime
        );
    }
}