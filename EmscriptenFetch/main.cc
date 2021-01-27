#include <stdio.h>
#include <string.h>
#include <string>
#include <emscripten.h>
#include <emscripten/fetch.h>
#include <emscripten/html5.h>
#include <emscripten/val.h>

void setInput (const char *fieldname, const char *value)
{
  emscripten::val document = emscripten::val::global("document");
  emscripten::val elem = document.call<emscripten::val>("getElementById", std::string(fieldname));
  if(!elem) printf("no elem");
                   
  elem.set("innerText", std::string(value));
}

void DisplayFetchedData(emscripten_fetch_t *fetch)
{
  ((char*)fetch->data)[fetch->numBytes]='\0';
    
  printf ("%s\n", fetch->data);
  setInput("output", fetch->data);
}

void downloadSucceeded(emscripten_fetch_t *fetch)
{
  printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);    
  DisplayFetchedData(fetch);  
  emscripten_fetch_close(fetch);
}

void downloadFailed(emscripten_fetch_t *fetch) {
  printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
  emscripten_fetch_close(fetch);
}

int on_load_click(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "GET");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_REPLACE;
  attr.onsuccess = downloadSucceeded;
  attr.onerror = downloadFailed;
  emscripten_fetch_t *fetch = emscripten_fetch(&attr, "https://gist.githubusercontent.com/camperbot/5a022b72e96c4c9585c32bf6a75f62d9/raw/e3c6895ce42069f0ee7e991229064f167fe8ccdc/quotes.json");   

  return 0;
}

int main(void)
{
  emscripten_set_click_callback("#load", (void*) 0, 0, on_load_click);
  
  return 0;
}