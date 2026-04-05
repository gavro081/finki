namespace Web.Response;

public record BasicConsultationsResponse
(
    Guid Id, 
    Guid RoomId, 
    DateTime Start, 
    DateTime End
    );