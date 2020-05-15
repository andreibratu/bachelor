using lab8.Models;

namespace lab8.DTOs
{
    public class DocumentOutputDTO
    {
        public DocumentOutputDTO(Document document)
        {
            this.Title = document.Title;
            this.FileUrl = document.FileUrl;
            this.Extension = document.Extension;
            this.Type = document.Type;
            this.Id = document.Id;
            this.Author = new UserOutputDTO(document.Author);
        }

        public int Id { get; set; }
        public string Title { get; set; }
        public string FileUrl { get; set; }

        public string Extension { get; set; }

        public string Type { get; set; }

        public UserOutputDTO Author { get; set; }
    }
}
