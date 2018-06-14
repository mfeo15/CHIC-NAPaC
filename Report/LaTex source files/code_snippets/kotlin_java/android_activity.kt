override fun onResume() {
    super.onResume()
    Client.getInstance().addNewObserver(this)
}

override fun onPause() {
    super.onPause()
    Client.getInstance().deleteAnObserver(this)
}