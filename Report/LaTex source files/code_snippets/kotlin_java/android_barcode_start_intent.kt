button_scan.setOnClickListener {
    val i = Intent(context, BarcodeCaptureActivity::class.java)
    startActivityForResult(i, BARCODE_READER_REQUEST_CODE)
}