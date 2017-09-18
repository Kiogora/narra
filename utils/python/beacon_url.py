# -*- coding: utf-8 -*-
import urllib
import json

#Contact bitsoko.co.ke with your device ID or list of.
url = "https://bitsoko.co.ke/devices/?dID=240ac404a672"

def get_short_url():
    response = urllib.urlopen(url)
    data = json.loads(response.read())
    return data['shortUrl']

if __name__=='__main__':
    print (get_short_url())


