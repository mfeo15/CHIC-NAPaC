override fun onActivityResult(request: Int, 
                              result: Int, data: Intent?) 
{
    // Check if the result is related to barcode before                          
    if (request != BARCODE_READER_REQUEST_CODE) 
        super.onActivityResult(request, result, data)
                              
                
    // Check for result correctness before accepting it              
    if (result == CommonStatusCodes.SUCCESS && data != null) 
    {
        val b_obj = BarcodeCaptureActivity.BarcodeObject
        val barcode = data.getParcelableExtra<Barcode>(b_obj)
        val p = barcode.cornerPoints
                
        passTheCodeToTheNextActivity(barcode.displayValue)
    }
}