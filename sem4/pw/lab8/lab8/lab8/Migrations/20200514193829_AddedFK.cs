using Microsoft.EntityFrameworkCore.Migrations;

namespace lab8.Migrations
{
    public partial class AddedFK : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Document_Users_AuthorId",
                table: "Document");

            migrationBuilder.DropColumn(
                name: "Token",
                table: "Users");

            migrationBuilder.AlterColumn<long>(
                name: "AuthorId",
                table: "Document",
                nullable: false,
                oldClrType: typeof(long),
                oldType: "bigint",
                oldNullable: true);

            migrationBuilder.AddForeignKey(
                name: "FK_Document_Users_AuthorId",
                table: "Document",
                column: "AuthorId",
                principalTable: "Users",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Document_Users_AuthorId",
                table: "Document");

            migrationBuilder.AddColumn<string>(
                name: "Token",
                table: "Users",
                type: "text",
                nullable: true);

            migrationBuilder.AlterColumn<long>(
                name: "AuthorId",
                table: "Document",
                type: "bigint",
                nullable: true,
                oldClrType: typeof(long));

            migrationBuilder.AddForeignKey(
                name: "FK_Document_Users_AuthorId",
                table: "Document",
                column: "AuthorId",
                principalTable: "Users",
                principalColumn: "Id",
                onDelete: ReferentialAction.Restrict);
        }
    }
}
