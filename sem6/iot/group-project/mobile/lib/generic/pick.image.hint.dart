import 'dart:io';
import 'dart:ui';

import 'package:flutter/material.dart';
import 'package:hexcolor/hexcolor.dart';
import 'package:image_picker/image_picker.dart';

import 'image.source.overlay.dart';

class PickImageHint extends StatelessWidget {
  final Function onImagePickedCallback;
  // Return overlay to parent so it can manage state
  final Function overlayLifecycleCallback;
  final double height;
  final File backgroundImage;
  final double width;
  final _picker = ImagePicker();

  PickImageHint(
      {@required this.onImagePickedCallback,
      @required this.overlayLifecycleCallback,
      @required this.backgroundImage,
      @required this.height,
      @required this.width});

  void _onImageSourcePicked(ImageSource source) async {
    if (source != null) {
      final pickedFile = await _picker.getImage(source: source);
      if (pickedFile != null) {
        onImagePickedCallback(File(pickedFile.path));
      }
    }
    overlayLifecycleCallback(null);
  }

  @override
  Widget build(BuildContext context) {
    Widget iconButton = IconButton(
        icon: Icon(
          Icons.add_a_photo,
          size: 30,
          color: Colors.white,
        ),
        onPressed: () async {
          FocusScope.of(context).unfocus(); // Bring down the keyboard
          var overlay =
              ImageSourceOverlay.show(context, this._onImageSourcePicked);
          overlayLifecycleCallback(overlay);
        });

    return this.backgroundImage != null
        ? Container(
            padding: EdgeInsets.symmetric(vertical: 5),
            width: width,
            height: height,
            decoration: BoxDecoration(
              image: DecorationImage(
                  colorFilter: ColorFilter.mode(
                      Colors.black.withOpacity(1), BlendMode.dstATop),
                  image: FileImage(backgroundImage),
                  fit: BoxFit.cover),
            ),
            child: iconButton)
        : Container(
            padding: EdgeInsets.symmetric(vertical: 5),
            color: HexColor("#bfbfbf"),
            width: width,
            height: height,
            child: iconButton);
  }
}
