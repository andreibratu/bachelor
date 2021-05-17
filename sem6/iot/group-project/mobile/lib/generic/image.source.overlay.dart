import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';

class ImageSourceOverlay {
  Function callback;
  OverlayEntry _displayScreen;

  ImageSourceOverlay.show(BuildContext context, Function callback) {
    this.callback = callback;
    _displayScreen =
        OverlayEntry(builder: (context) => _buildWidget(context, callback));
    Overlay.of(context).insert(_displayScreen);
  }

  Widget _buildWidget(BuildContext context, Function callback) {
    return GestureDetector(
        onTap: () {
          _displayScreen.remove();
          callback(null);
        },
        child: Container(
            width: double.infinity,
            height: double.infinity,
            color: Color.fromRGBO(0, 0, 0, 0.6),
            alignment: Alignment.bottomCenter,
            child: Column(mainAxisAlignment: MainAxisAlignment.end, children: [
              GestureDetector(
                  onTap: () {
                    _displayScreen.remove();
                    callback(ImageSource.gallery);
                  },
                  child: Container(
                      color: Colors.black,
                      height: MediaQuery.of(context).size.height / 10,
                      width: double.infinity,
                      padding: EdgeInsets.symmetric(horizontal: 10),
                      child: Row(
                        crossAxisAlignment: CrossAxisAlignment.center,
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        children: [
                          Icon(Icons.image, color: Colors.white),
                          Text("Gallery",
                              style:
                                  TextStyle(fontSize: 10, color: Colors.white))
                        ],
                      ))),
              GestureDetector(
                  onTap: () {
                    _displayScreen.remove();
                    callback(ImageSource.camera);
                  },
                  child: Container(
                      height: MediaQuery.of(context).size.height / 10,
                      width: double.infinity,
                      color: Colors.black,
                      padding: EdgeInsets.symmetric(horizontal: 10),
                      child: Row(
                        crossAxisAlignment: CrossAxisAlignment.center,
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        children: [
                          Icon(Icons.camera_alt, color: Colors.white),
                          Text("Take a picture",
                              style:
                                  TextStyle(fontSize: 10, color: Colors.white))
                        ],
                      ))),
            ])));
  }

  void dispose() {
    this._displayScreen.remove();
  }
}
