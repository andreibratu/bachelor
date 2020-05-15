namespace lab8.DTOs
{
    public class DocumentInputDTO
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string Extension { get; set; }
        // The file will be passed as hexadecimal
        public string File { get; set; }
        public string Type { get; set; }
    }
}
