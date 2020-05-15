using System;
using Microsoft.EntityFrameworkCore.Migrations;

namespace lab8.Migrations
{
    public partial class ChangedFileByteArrayFileUrlColumn : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "File",
                table: "Document");

            migrationBuilder.AddColumn<string>(
                name: "FileUrl",
                table: "Document",
                nullable: false);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "FileUrl",
                table: "Document");

            migrationBuilder.AddColumn<byte[]>(
                name: "File",
                table: "Document",
                type: "varbinary(4000)",
                nullable: false,
                defaultValue: new byte[] {  });
        }
    }
}
