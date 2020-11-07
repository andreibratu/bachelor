from flask import Flask, jsonify, abort, request
from markupsafe import escape

app = Flask(__name__)
entries = []


@app.route("/", strict_slashes=False)
def hello_world():
    return "Hello, World!"


@app.route("/api/entries", methods=["GET"], strict_slashes=False)
def get_entries():
    global entries
    return jsonify(entries)


@app.route("/api/entries", methods=["POST"], strict_slashes=False)
def add_entry():
    global entries
    new_entry = request.get_json(force=True)
    entries.append(new_entry)
    return jsonify(new_entry), 201


@app.route("/api/entries/<entry_id>", methods=["GET"], strict_slashes=False)
def get_entry(entry_id):
    global entries
    try:
        entry_id = int(escape(entry_id))
        return jsonify([e for e in entries if e["id"] == entry_id][0])
    except (IndexError, ValueError):
        abort(404)


@app.route("/api/entries/<entry_id>", methods=["DELETE"], strict_slashes=False)
def delete_entry(entry_id):
    global entries
    try:
        entry_id = int(escape(entry_id))
        if not any([e["id"] == entry_id for e in entries]):
            abort(404)
        entries = [e for e in entries if e["id"] != entry_id]
        return "", 200
    except ValueError:
        abort(404)


@app.route("/api/entries/<entry_id>", methods=["PUT"], strict_slashes=False)
def update_entry(entry_id):
    global entries
    try:
        entry_id = int(escape(entry_id))
        if not any([e["id"] == entry_id for e in entries]):
            abort(404)
        updated_request = request.get_json(force=True)
        entries = [e for e in entries if e["id"] != entry_id]
        entries.append(updated_request)
        return jsonify(updated_request), 200
    except ValueError:
        abort(404)


if __name__ == "__main__":
    app.run()