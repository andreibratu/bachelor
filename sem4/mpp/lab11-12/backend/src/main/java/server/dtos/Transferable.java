package server.dtos;

public interface Transferable<T>
{
    DTO<T> toDTO();
}
