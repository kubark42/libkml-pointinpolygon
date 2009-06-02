// Copyright 2009, Google Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. Neither the name of Google Inc. nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file contains the declaration of some convenience functions for
// processing Atom and Atom with KML.  While no code here is specific to
// the Google Maps Data API much of this is useful in coding to that service.
// See RFC 4287 for more information about Atom.

#ifndef KML_CONVENIENCE_ATOM_UTIL_H_
#define KML_CONVENIENCE_ATOM_UTIL_H_

#include <string>
#include "kml/dom.h"

namespace kmlconvenience {

// This class is an API of Atom (RFC 4287) utility functions especially with
// particular emphasis on wrapping KML.
class AtomUtil {
 public:
  // This creates an <atom:entry> with the specified values for <atom:title>
  // and <atom:summary>.
  static kmldom::AtomEntryPtr CreateBasicEntry(const std::string& title,
                                               const std::string& summary);

  // This creates an <atom:entry> from and for the KML Feature.  The
  // <atom:entry>'s <atom:title> is set from the Feature's <name> and the
  // <atom:summary> is set from the Feature's <description>.
  static kmldom::AtomEntryPtr CreateEntryForFeature(
      const kmldom::FeaturePtr& feature);

  // This returns the <atom:entry>'s <atom:content>'s src= and returns true
  // if these exist.  False is returned if the <atom:entry> has no
  // <atom:content> or if the <atom:content> has no src=.  Passing a NULL
  // src is safe and has no bearing on the return value.
  static bool GetContentSrc(const kmldom::AtomEntryPtr& entry,
                            std::string* src);

  // This returns the href= value of the first <atom:link> whose first rel=
  // ends with the given link relation type.  Both AtomFeed (<atom:feed>)
  // and AtomEntry (<atom:entry>) are of the AtomCommon type.
  static bool FindRelUrl(const kmldom::AtomCommon& atom_common,
                         const std::string& rel_type, std::string* href);

  // This returns a clone of the KML Feature contained in the <atom:entry>.
  // The returned clone Feature's <atom:link> is set to the <atom:entry>'s
  // "self" link relation if such is found in the <atom:entry>.
  // NULL is returned if no KML Feature is contained by this <atom:entry>.
  static kmldom::FeaturePtr CloneEntryFeature(
      const kmldom::AtomEntryPtr& entry);

  // This simply gets the KML Feature in the <atom:entry> if it has one.
  // See CloneEntryFeature() for a slightly richer function for use in
  // reconstructing a KML file from one or more <atom:entry>'s.  Note: since
  // this feature is the child of another element it cannot be directly
  // parented to any other element, hence the use of kmlengine::Clone()
  // in the CloneEntryFeature() function.
  static kmldom::FeaturePtr GetEntryFeature(const kmldom::AtomEntryPtr& entry);

  // This calls CloneEntryFeature() for each <atom:entry> in the <atom:feed>.
  // The Container's <atom:link> is set to the <atom:feed>'s "self" link
  // relation if such is found in the <atom:feed>.
  static void GetFeedFeatures(const kmldom::AtomFeedPtr& feed,
                              kmldom::ContainerPtr container);
};

}  // end namespace kmlconvenience 

#endif  // KML_CONVENIENCE_ATOM_UTIL_H
